from model import get_model
import torch
from data_loader import prepareTestData, load_class_names
import argparse


def load_weight(model, path):
    sd = torch.load(path)
    model.load_state_dict(sd)


def main(conf):
    device = torch.device(conf.cuda)
    classes = load_class_names(conf.meta)
    model = get_model(len(classes), conf.arch)
    model = model.to(device)
    model.eval()
    load_weight(model, conf.weight)
    testData = prepareTestData(conf.imgdir, conf.annos, (conf.size, conf.size))

    sum = 0
    total_num = 0
    with torch.no_grad():  # Context-manager that disabled gradient calculation
        for i, (input, target) in enumerate(testData):
            input = input.to(device)
            target = target.to(device)
            pred = model(input)
            sum += pred.max(1)[1].eq(target).float().sum()
            total_num += len(target)
        print(f"The accuracy is {sum / total_num}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(allow_abbrev=False)
    parser.add_argument(
            '--arch', type=str, action='store', required=False,
            help='选择一个网络model', default='resnet34',
            choices=['resnet18', 'resnet34'])
    parser.add_argument(
            '--imgdir', type=str, action='store', required=False,
            help='测试图片目录', default='./cars_test')
    parser.add_argument(
            '--annos', type=str, action='store', required=False,
            help='测试图片信息文件路径(cars_test_annos.mat)',
            default='./devkit/cars_test_annos.mat')
    parser.add_argument(
            '--meta', type=str, action='store', required=False,
            help='汽车名称和编号对应的文件路径(cars_meta.mat)',
            default='./devkit/cars_meta.mat')
    parser.add_argument(
            '--weight', type=str, action='store', required=False,
            help='网络要加载的参数文件路径', default='./best.pt')
    parser.add_argument(
            '--cuda', type=str, action='store', required=False,
            help='使用哪一块GPU, (e.g. "cuda:0")', default='cuda:0')
    parser.add_argument(
            '--size', type=int, action='store', required=False,
            help='图片尺寸', default=400, choices=[400, 224])
    args = parser.parse_args()
    main(args)
