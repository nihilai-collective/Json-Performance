
----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2558.37 | 0.275953 | 8720.34ms | 7351818 | 80 | 4.57534e+09 | 2.74052e+06 | 1.01183 | 0.967693 | 1(Win) | true |
| Jsonifier (two-stage) | 2535.9 | 0.13316 | 8597.29ms | 7351818 | 30 | 4.06624e+08 | 2.7648e+06 | 1.11606 | 0.976178 | 2(Loss) | true |
| simdjson (ondemand) | 2072.38 | 0.140619 | 5146.55ms | 7351818 | 30 | 6.78985e+08 | 3.38318e+06 | 0.748535 | 1.19451 | 3(Loss) | true |
| Glaze | 2023.22 | 0.418571 | 5285.43ms | 7351818 | 30 | 6.31192e+09 | 3.46538e+06 | 1.93116 | 1.22356 | 4(Loss) | true |
