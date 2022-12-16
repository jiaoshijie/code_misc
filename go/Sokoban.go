package main

import (
	"fmt"
	"os"
	"os/exec"
)

type G_Player struct {
  x int
  y int
}

const c_sp = 0  // space
const c_wa = 1  // wall
const c_tg = 2  // target
const c_bo = 3  // box
const c_ma = 4  // man
const c_bt = 5  // box and target
const c_mt = 6  // man and target

// Global var
var g_iface = [8][6]int{ {c_wa, c_wa, c_wa, c_wa, c_wa, c_wa},
                         {c_wa, c_tg, c_tg, c_tg, c_wa, c_wa},
                         {c_wa, c_wa, c_bo, c_sp, c_wa, c_wa},
                         {c_wa, c_wa, c_ma, c_sp, c_wa, c_wa},
                         {c_wa, c_sp, c_bo, c_bo, c_sp, c_wa},
                         {c_wa, c_sp, c_sp, c_sp, c_wa, c_wa},
                         {c_wa, c_sp, c_sp, c_wa, c_wa, c_wa},
                         {c_wa, c_wa, c_wa, c_wa, c_wa, c_wa} }

var g_userPos = G_Player{3, 2}
var g_close = 0

func update_iface() {
  for i := 0; i < 8; i++ {
    for j := 0; j < 6; j++ {
      switch g_iface[i][j] {
      case c_sp:
        fmt.Printf("%v", "   ")
      case c_wa:
        fmt.Printf("%v", "███")
      case c_tg:
        fmt.Printf("%v", "░□░")
      case c_bo:
        fmt.Printf("%v", "░■░")
      case c_ma:
        fmt.Printf("%v", "┃♀┃")
      case c_bt:
        fmt.Printf("%v", "▒▣▒")
      case c_mt:
        fmt.Printf("%v", "▓♀▓")
      }
    }
    fmt.Println()
  }
}

func init_game() {
  update_iface()
}

func is_move(x int, y int, x_m int, y_m int) (bool) {
  if (x >= 8 || y >= 6) { return false }

  if (g_iface[x][y] == c_wa) {
    return false
  } else if (g_iface[x][y] == c_sp || g_iface[x][y] == c_tg) {
    return true
  } else {
    return is_move(x + x_m, y + y_m, x_m, y_m)
  }
}

func move_box(x_box int, y_box int, x_m int, y_m int) {
  var temp = g_iface[x_box + x_m][y_box + y_m]
  if (temp == c_sp || temp == c_tg) {  // space and target
    g_iface[x_box][y_box] -= c_bo
    g_iface[x_box + x_m][y_box + y_m] += c_bo
  }
}

func move(x_m int, y_m int) {
  var temp = g_iface[g_userPos.x + x_m][g_userPos.y + y_m]
  if (temp == c_bo || temp == c_bt) { // box and box_target
    move_box(g_userPos.x + x_m, g_userPos.y + y_m, x_m, y_m)
  }
  temp = g_iface[g_userPos.x + x_m][g_userPos.y + y_m]
  if (temp == c_sp || temp == c_tg) {  // space and target
    g_iface[g_userPos.x][g_userPos.y] -= c_ma
    g_iface[g_userPos.x + x_m][g_userPos.y + y_m] += c_ma
    g_userPos.x += x_m
    g_userPos.y += y_m
  }
}

func user_move() {
  var ch string
  fmt.Scanf("%v", &ch)
  switch ch[0] {
  case 'w':  // up
    if (is_move(g_userPos.x - 1, g_userPos.y, -1, 0)) {
      move(-1, 0)
    }
  case 's':  // down
    if (is_move(g_userPos.x + 1, g_userPos.y, 1, 0)) {
      move(1, 0)
    }
  case 'a':  // left
    if (is_move(g_userPos.x, g_userPos.y - 1, 0, -1)) {
      move(0, -1)
    }
  case 'd':  // right
    if (is_move(g_userPos.x, g_userPos.y + 1, 0, 1)) {
      move(0, 1)
    }
  case 'c':
    g_close = 1
    return
  default:
    // do nothing
  }
  clear()
  update_iface()
}

func main() {
  clear()
  init_game()
  for g_close == 0 {
    user_move()
    if (g_iface[1][1] == 5 && g_iface[1][2] == 5 && g_iface[1][3] == 5) {
      fmt.Println("You win!!!")
      g_close = 1
    }
  }
}

func clear() {
  cmd := exec.Command("clear")
  cmd.Stdout = os.Stdout
  cmd.Run()
}
