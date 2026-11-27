
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 7033.41 | 0.320649 | 770.127ms | 3808 | 1280 | 3508.58 | 516.334 | 0.129383 | 0.790391 | 3.19039 | 0.387868 | 0.000266093 | 2.87224e-05 | 3.48772e-06 | 1(Win) | true |
| Jsonifier | 6974.65 | 0.220728 | 768.045ms | 3808 | 320 | 422.681 | 520.684 | 0.116897 | 0.797175 | 3.19039 | 0.387868 | 0.000262605 | 5.17004e-05 | 2.21573e-05 | 2(Loss) | true |
| simdjson (ondemand) | 6929.92 | 0.0554125 | 766.346ms | 3808 | 1280 | 107.935 | 524.045 | 0.101179 | 0.800377 | 3.25263 | 0.31959 | 0.00029502 | 1.37457e-05 | 2.25676e-06 | 3(Loss) | true |
| simdjson (reflection) | 6780.58 | 0.15876 | 772.172ms | 3808 | 80 | 57.8403 | 535.587 | 0.109572 | 0.814447 | 3.24475 | 0.324317 | 0.000279018 | 3.61082e-05 | 6.56513e-06 | 4(Loss) | true |
| Glaze | 3564.53 | 0.104783 | 817.82ms | 3808 | 2560 | 2917.52 | 1018.81 | 0.224068 | 1.49749 | 6.53151 | 1.19433 | 0.000264554 | 3.23127e-05 | 1.41561e-05 | 5(Loss) | true |
