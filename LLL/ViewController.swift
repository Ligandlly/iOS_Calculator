//
//  ViewController.swift
//  LLL
//
//  Created by LLy on 2019/5/31.
//  Copyright © 2019 GTEGZGX-BXBWRCF. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    var cursorIndex = 0
    var isAnswer = false
    @IBOutlet var numberButton: [UIButton]!
    @IBOutlet weak var label: UILabel!
    override func viewDidLoad() {
//        label.text = 𝙸"
        label.text = "🔫"
        super.viewDidLoad()
        // Do any additional setup after loading the view.
    }

    @IBAction func buttonTaped(_ sender: UIButton) {
        if !isAnswer && self.label.text!.count < 21{
            let color = sender.backgroundColor!
            sender.backgroundColor = .orange
            DispatchQueue.main.asyncAfter(deadline: .now()+0.05, execute:
                {
                    sender.backgroundColor = color
            })
            if let tempTitle = sender.title(for: .normal), let tempLabel = self.label.text{
                var left = String(tempLabel.prefix(self.cursorIndex))
                let right = String(tempLabel.suffix(tempLabel.count - self.cursorIndex))
                left = left + tempTitle
                self.label.text = left + right
                self.cursorIndex += 1
            }
        }
    }
    
    @IBAction func deleteTaped(_ sender: UIButton) {
        if !isAnswer {
            if self.cursorIndex > 0 {
                if let tempLabel = self.label.text {
                    var left = String(tempLabel.prefix(self.cursorIndex))
                    let right = String(tempLabel.suffix(tempLabel.count - self.cursorIndex))
                    let _ = left.popLast()
                    self.label.text = left + right
                    self.cursorIndex -= 1
                }
            } // end inner if
        } // end if
    }
    
    @IBAction func moveLeft(_ sender: Any) {
        if !isAnswer {
            if self.cursorIndex > 0 {
                if let tempLabel = self.label.text {
                    var left = String(tempLabel.prefix(self.cursorIndex))
                    var right = String(tempLabel.suffix(tempLabel.count - self.cursorIndex))
                    right.insert(left.last!, at: right.index(right.startIndex, offsetBy: 1))
                    let _ = left.popLast()
                    self.label.text = left + right
                    self.cursorIndex -= 1
                } // end unwrapper
            } // end inner if
        } // end if
    }
    
    @IBAction func moveRight(_ sender: Any) {
        if !isAnswer {
            if let tempLabel = self.label.text {
                if self.cursorIndex < tempLabel.count - 1 {
                    var left = String(tempLabel.prefix(self.cursorIndex))
                    var right = String(tempLabel.suffix(tempLabel.count - self.cursorIndex))
                left.append(right[right.index(right.startIndex, offsetBy: 1)])
                    right.remove(at: right.index(right.startIndex, offsetBy: 1))
                    self.label.text = left + right
                    self.cursorIndex += 1
                }
            }
        }
    }
    
    @IBAction func ACTapped(_ sender: Any) {
        self.label.text = "🔫"
        self.cursorIndex = 0
        if isAnswer {
            isAnswer = false
        }
    }
    
    @IBAction func equaltionTapped(_ sender: Any) {
        if !isAnswer {
            if var s = self.label.text {
                s.remove(at: s.firstIndex(of: "🔫")!)
                if s.first != "+" {
                    s = "+" + s
                }
                s = s.replacingOccurrences(of: "×", with: "*")
                s = s.replacingOccurrences(of: "÷", with: "/")
                let ans = "= " + String(wrapper(s))
                self.label.text = ans
                self.isAnswer = true
            }
        }
    }
    
}
