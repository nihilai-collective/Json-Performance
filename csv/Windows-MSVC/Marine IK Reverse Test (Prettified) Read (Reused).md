
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2315.33 | 0.213098 | 5374.44ms | 7351818 | 40 | 1.66565e+09 | 3.02819e+06 | 0.786728 | 1.31261 | 1(Win) | true |
| Jsonifier | 2194.9 | 0.803002 | 5454.42ms | 7351818 | 40 | 2.63181e+10 | 3.19434e+06 | 0.155228 | 1.38465 | 2(Loss) | true |
| Glaze | 1144.56 | 0.488874 | 9594.85ms | 7351818 | 80 | 7.17456e+10 | 6.1257e+06 | 0.958591 | 2.65533 | 3(Loss) | true |
| simdjson (ondemand) | 728.536 | 0.280942 | 7425.1ms | 7351818 | 30 | 2.19302e+10 | 9.62374e+06 | 2.122 | 4.17193 | 4(Loss) | true |
