
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 735.112 | 0.349063 | 8663.44ms | 1834197 | 80 | 5.51927e+09 | 2.37954e+06 | 1.22945 | 3.36784 | 1(Win) | true |
| Jsonifier (two-stage) | 670.947 | 0.131782 | 9408.64ms | 1834197 | 30 | 3.54119e+08 | 2.6071e+06 | 0.0763995 | 3.68991 | 2(Loss) | true |
| Glaze | 212.109 | 1.21825 | 6088.41ms | 1834197 | 40 | 4.03741e+11 | 8.24682e+06 | 0.812021 | 11.6721 | 3(Loss) | true |
| simdjson (ondemand) | 134.557 | 0.159484 | 9417.42ms | 1834197 | 40 | 1.71938e+10 | 1.29999e+07 | 1.72562 | 18.3994 | 4(Loss) | true |
