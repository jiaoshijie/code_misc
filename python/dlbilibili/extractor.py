import req
import re
import json

# video api
bilibiliBangumiAPI = "https://api.bilibili.com/pgc/player/web/playurl?"


class biliExtractor:
    def genAPI(self, op):
        params = "avid={}&bvid={}&cid={}&qn={}&fnver=0&fnval=2000&fourk=1".format(
            op["aid"], op["bvid"], op["cid"], op["qn"])
        return bilibiliBangumiAPI + params

    def getMimeType(self, data):
        if "mime_type" in data:
            temp = data['mime_type']
        elif "mimeType" in data:
            temp = data['mimeType']
        else:
            return "mp4"
        return re.search('.+/(.+)', temp).group(1)

    def get_playlist(self, url):
        html, err = req.Get(url)
        if err != 0:
            print(err)
            exit(1)
        info = re.search(
            r"window.__INITIAL_STATE__=(.+);\(function", html.text).group(1)
        js = json.loads(info)
        episodes = []
        for item in js["sections"][0]["episodes"]:
            """
            dict_keys(['title', 'bvid'])
            """
            episodes.append(item["bvid"])
        # print("' '".join(episodes))

        with open("./d.sh", "w") as f:
            f.write(f"""#!/usr/bin/env bash\n\n
file_name=1
for i in '{"' '".join(episodes)}'; do
    # echo "$i"
    # lux -c c.txt -i $i
    # break
    lux -c c.txt -f 116-12 -O "$file_name" "$i" || break
    ((file_name++))
done
""")



    def Extractor(self, url):
        html, err = req.Get(url)
        if err != 0:
            print(err)
            exit(1)
        info = re.search(
            r"window.__INITIAL_STATE__=(.+);\(function", html.text).group(1)
        js = json.loads(info)
        option = {"aid": js["epInfo"]["aid"], "bvid": js["epInfo"]
                  ["bvid"], "cid": js["epInfo"]["cid"]}
        option["qn"] = 64
        jsonstring, err = req.Get(self.genAPI(option))
        if err != 0:
            print(err)
            exit(1)
        jstring = json.loads(jsonstring.text)
        dashInfo = {"cur_quality": jstring['result']['quality'], "quality": jstring['result']
                    ['accept_quality'], "description": jstring['result']['accept_description'], "dash": jstring['result']['dash']}
        # print(dashInfo['dash']['audio'][0]['mimeType'])
        download_info = {
            'audio': {"url": dashInfo['dash']['audio'][0]['baseUrl']}, 'video': {}}
        tempW = dashInfo['dash']['audio'][0]['bandwidth']
        for i in range(1, len(dashInfo['dash']['audio'])):
            if tempW < dashInfo['dash']['audio'][i]['bandwidth']:
                download_info['audio']['url'] = dashInfo['dash']['audio'][i]['baseUrl']
            download_info['audio']['type'] = self.getMimeType(
                dashInfo['dash']['audio'][i])
        s, err = req.Size(download_info['audio']['url'])
        if err != 0:
            print(err)
            exit(1)
        download_info['audio']['size'] = s
        # print(dashInfo['dash']['video'][0].keys())
        # TODO
        for v in dashInfo['dash']['video']:
            if v['id'] == 64:
                download_info['video']['url'] = v['base_url']
                download_info['video']['type'] = self.getMimeType(v)

        s, err = req.Size(download_info['video']['url'])
        if err != 0:
            print(err)
            exit(1)
        download_info['video']['size'] = s
        return download_info
