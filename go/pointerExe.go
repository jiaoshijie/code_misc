package main

import (
  "fmt"
  "os"
  "os/exec"
  // "time"
  "bufio"
  "strconv"
)


type Node struct {
  num int
  name string
  next *Node
}

type Head struct {
  sum int
  next *Node
}


var g_close = false
const data_file = "./data_file"


func main() {
  var head *Head = nil
  for g_close == false {
    clear()
    menu()
    var ch string
    fmt.Scanf("%s", &ch)
    if len(ch) != 0 {
      switch ch[0] {
      case '1':
        if head == nil {
          head = init_list()
        }
      case '2':
        print_list(head)
      case '3':
        var num int
        reader := bufio.NewReader(os.Stdin)
        fmt.Printf("Enter the num: ")
        fmt.Scanf("%d", &num)
        fmt.Printf("Enter the name: ")
        name, err := reader.ReadString('\n')
        if err != nil {
          fmt.Println("failed")
          return
        }
        tail_insert_node(head, num, name)
      case '4':
        if delete_node(head) {
          fmt.Println("delete succeed!!!")
        } else {
          fmt.Println("failed to delete!!!")
        }
      case '5':
        readDataFromFile(head)
      case '6':
        writeDateToFile(head)
      case '7':
        quit()
        continue
      default:
        continue
        // do nothing
      }
    }
    fmt.Printf("Press any key to continue!!!")
    fmt.Scanln()
  }
  clear()
  fmt.Println("SS: See you later!!!")
}


// clear console content
func clear() {
  cmd := exec.Command("clear")
  cmd.Stdout = os.Stdout
  cmd.Run()
}

func menu() {
  fp := fmt.Println
  fp("*****MENU*****")
  fp("")
  fp("1. 初始化系统")
  fp("2. 打印数据")
  fp("3. 插入数据")
  fp("4. 删除数据 by num")
  fp("5. 读数据")
  fp("6. 写数据")
  fp("7. 退出")
  fp("")
  fmt.Printf("Enter the number you want to do: ")
}


func print_list(head *Head) {
  if head == nil {
    return
  }
  temp := head.next
  for temp != nil {
    fmt.Printf("%v name is %v", temp.num, temp.name)
    temp = temp.next
  }
}


func init_list() (*Head) {
  temp := new(Head)
  temp.sum = 0
  temp.next = nil
  return temp
}

func tail_insert_node(head *Head, num int, name string) {
  if head == nil {
    return
  }
  node := get_node(num, name)
  if head.next == nil {
    head.next = node
  } else {
    temp := head.next
    for temp.next != nil {
      temp = temp.next
    }
    temp.next = node
  }
  head.sum++
}

func get_node(num int, name string) (*Node) {
  temp := new(Node)
  temp.num = num
  temp.name = name
  temp.next = nil
  return temp
}

func delete_node(head *Head) (bool) {  // TODO: Does need to free the unused node?
  var num int
  fmt.Printf("Enter the num you want to delete: ")
  fmt.Scanf("%d", &num)
  if head == nil || head.next == nil {
    return false
  }
  if head.next.num == num {
    head.next = head.next.next
    return true
  }
  temp := head.next
  for temp.next != nil && temp.next.num != num {
    temp = temp.next
  }
  if temp.next == nil { return false }
  temp.next = temp.next.next
  return true
}

func quit() {
  var quit_ch string
  fmt.Printf("Do you really want to quit[y/n]: ")
  fmt.Scanf("%s", &quit_ch)
  if len(quit_ch) != 0 {
    if quit_ch[0] == 'y' || quit_ch[0] == 'Y' { g_close = true }
  }
}

func readDataFromFile(head *Head) {
  file, err := os.Open(data_file)
  if err != nil {
    panic(err)
  }
  defer file.Close()
  scanner := bufio.NewScanner(file)
  for scanner.Scan() {
    num, name := divideString(scanner.Text())
    i, _ := strconv.Atoi(num)
    tail_insert_node(head, i, name + "\n")
  }
}

func divideString(str string) (string, string) {
  index := 0
  for str[index] != ',' {
    index++
  }
  return str[0: index], str[index + 1:]
}

func writeDateToFile(head *Head) {
  if head == nil || head.next == nil {
    fmt.Println("no data will be written!!!")
    return
  }
  file, err := os.Create(data_file)
  if err != nil {
    panic(err)
  }
  defer file.Close()
  temp := head.next
  for temp != nil {
    file.WriteString(fmt.Sprintf("%v,%v", temp.num, temp.name))
    temp = temp.next
  }
  fmt.Println("Data has been written.")
}
