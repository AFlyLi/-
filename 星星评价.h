ios 教你 星星评分（支持点击和滑动）［原创］

由于项目的需要，要设计能评分、要能显示评分数据的星级评分条。但是ios上好像没有这个控件，所以只有自己想办法解决。对于这个功能需求，我总共想了两个方法，

方法一：（这种方法比较愚）

思路：这种方法是直接在storyboard上的viewController里面直接建5个UIImageView，初始值图片设置为“button_star_white”。
第一步，在storyboard中的viewController上推拽5个人UIImageView，连接到 “ViewController. h” 文件中，作为viewController的成员变量代码如下：

@property (weak, nonatomic) IBOutlet UIImageView *myImageview1;

@property (weak, nonatomic) IBOutlet UIImageView *myImageview2;

@property (weak, nonatomic) IBOutlet UIImageView *myImageview2;

@property (weak, nonatomic) IBOutlet UIImageView *myImageview3;

@property (weak, nonatomic) IBOutlet UIImageView *myImageview4;

@property (weak, nonatomic) IBOutlet UIImageView *myImageview5;

第二步，为每个imageView添加点击事件，代码如下：

_myImageview1.userInteractionEnabled = YES;

UITapGestureRecognizer *singleTap1 = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(buttonpress1)];

[_myImageview1 addGestureRecognizer:singleTap1];

_myImageview2.userInteractionEnabled = YES;

UITapGestureRecognizer *singleTap1 = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(buttonpress2)];

[_myImageview2 addGestureRecognizer:singleTap1];

...

(5个imageView同样方式，再次不一一赘述)

第三步，实现方方法：buttonpress1，buttonpress2，…3,4,5，代码如下：


- (void) buttonpress1{
    
    _myImageview1.image = [UIImage imageNamed:@"button_star_red"];
    
    _myImageview2.image = [UIImage imageNamed:@"button_star_white"];
    
    _myImageview3.image = [UIImage imageNamed:@"button_star_white"];
    
    _myImageview4.image = [UIImage imageNamed:@"button_star_white"];
    
    _myImageview5.image = [UIImage imageNamed:@"button_star_white"];
    
}

- (void) buttonpress1{
    
    _myImageview1.image = [UIImage imageNamed:@"button_star_red"];
    
    _myImageview2.image = [UIImage imageNamed:@"button_star_red"];
    
    _myImageview3.image = [UIImage imageNamed:@"button_star_white"];
    
    _myImageview4.image = [UIImage imageNamed:@"button_star_white"];
    
    _myImageview5.image = [UIImage imageNamed:@"button_star_white"];
    
}

. . .

(5个imageView同样方式，再次不一一赘述)

好了，讲过上述的几个步骤，点击星星打分，就可以实现了，不过，说过了，这个方法很愚，因为重复代码的太多，而且还不支持滑动。下面我来介绍第二种方法。

方法二（这种方法相对高级一点，但是绝对不是最高级，我相信，优秀的马努，人才辈出）

思路：ios 中 touchesBegan和touchesMoved两个方法可以获取到UIView上的点击的坐标和滑动的坐标，根据坐标，位于X坐标左边的imageview设置为“button_star_red”，右边的设置为“button_star_red”。

第一步：在UIViewController上添加一个UIView（两种方式，直接拖拽或者在”.m”文件代码创建，这里直接拖拽）命名为：myview，width 为星星宽度的6倍（总共5颗星星，确保可以0分），heigh为星星的高度

1

@property (weak, nonatomic) IBOutlet UIView *myview;

第二步：在myview上添加imageview，将星星初始化为“button_star_white”，并且按顺序加入到数组中，便于后期遍历改变星星颜色，代码如下：


UIImageView *imageView;

for (int i = 0; i < 5; i++) {
    
    imageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"button_star_white"]];
    
    imageView.frame = CGRectMake(_myview.bounds.origin.x+((i+1)*24), _myview.bounds.origin.y, 24, 24);
    
    [_myview addSubview:imageView];
    
    [_allStar addObject:imageView];
    
}

第三步：获取点击活着滑动的坐标，根据坐标，将坐标X以左的星星置为“button_star_white”（星星的宽和高都是24，）

#pragma mark - 点击的坐标

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event

{
    
    UITouch *touch = [touches anyObject];
    
    CGPoint touchPoint = [touch locationInView:_myview];
    
    UIImageView *im ;
    
    for(int i = 0;i < 5 ; i++){
        
        im = _allStar[i];
        
        NSLog(@"_all[%i] = (%f,%f)",i,im.frame.origin.x,im.frame.origin.y);
        
        if ((touchPoint.x > 0)&&(touchPoint.x < 144)&&(touchPoint.y > 0)&&(touchPoint.y < 24)) {
            
            NSString *myscore = [NSString stringWithFormat:@"分数为：%i",((int)touchPoint.x)/24];
            
            _score.text = myscore;
            
            if (im.frame.origin.x > touchPoint.x) {
                
                im.image =[UIImage imageNamed:@"button_star_white"];
                
            }else{
                
                im.image =[UIImage imageNamed:@"button_star_red"];
                
            }
            
        }
        
    }
    
}

#pragma mark - 滑动的坐标

-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event{
    
    UITouch *touch = [touches anyObject];
    
    CGPoint touchPoint = [touch locationInView:_myview];
    
    UIImageView *im ;
    
    for(int i = 0;i < 5 ; i++){
        
        im = _allStar[i];
        
        NSLog(@"_all[%i] = (%f,%f)",i,im.frame.origin.x,im.frame.origin.y);
        
        if ((touchPoint.x > 0)&&(touchPoint.x < 144)&&(touchPoint.y > 0)&&(touchPoint.y < 24)) {
            
            NSString *myscore = [NSString stringWithFormat:@"分数为：%i",((int)touchPoint.x)/24];
            
            _score.text = myscore;
            
            if (im.frame.origin.x > touchPoint.x) {
                
                im.image =[UIImage imageNamed:@"button_star_white"];
                
            }else{
                
                im.image =[UIImage imageNamed:@"button_star_red"];
                
            }
            
        }
        
    }
    
}

怎么样，与第一种方法，第二种方法效果是不是更智能，过程更明了。细心的读者会发现第二种方式的打分还可以支持小数。

附上星星图片，三种尺寸button_star_red button_star_red@2x button_star_red@3x button_star_white button_star_white@2x button_star_white@3x

本文永久地址：http://blog.it985.com/13038.html
本文出自 IT985博客 ，转载时请注明出处及相应链接。