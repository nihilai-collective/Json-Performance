
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1334.94 | 0.215368 | 90.7641ms | 1213 | 640 | 2229.17 | 866.562 | 0 | 1.80117 | 1(Win) | true |
| Glaze | 398.899 | 0.123468 | 303.349ms | 1213 | 40 | 512.821 | 2900 | 0.115075 | 6.11307 | 2(Loss) | true |
| simdjson (ondemand) | 286.693 | 0.189284 | 420.816ms | 1213 | 40 | 2333.33 | 4035 | 0.373134 | 8.58234 | 3(Loss) | true |
