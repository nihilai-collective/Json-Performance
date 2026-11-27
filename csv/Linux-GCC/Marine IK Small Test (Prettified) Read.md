
----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2671.42 | 0.20285 | 654.929ms | 18245 | 2560 | 446882 | 6513.3 | 0.0629924 | 0.922822 | 1(Win) | true |
| Jsonifier | 2615.18 | 0.413579 | 698.146ms | 18245 | 640 | 484598 | 6653.39 | 0.424105 | 0.94285 | 2(Loss) | true |
| simdjson (reflection) | 2311.76 | 0.155662 | 736.349ms | 18245 | 40 | 5490.75 | 7526.65 | 0.15057 | 1.06728 | 3(Loss) | true |
| simdjson (ondemand) | 1793.62 | 0.11721 | 949.124ms | 18245 | 40 | 5171.51 | 9700.92 | 0.560024 | 1.37631 | 4(Loss) | true |
| Glaze | 1755.65 | 0.0607649 | 998.43ms | 18245 | 40 | 1450.71 | 9910.75 | 0.0455526 | 1.40627 | 5(Loss) | true |
