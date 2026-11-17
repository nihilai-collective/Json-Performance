
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2597.28 | 0.0511089 | 1042.18ms | 25388 | 4890 | 111000 | 9322.02 | 0.187865 | 1.16744 | 1(Win) | true |
| Jsonifier | 2444.6 | 0.0883234 | 1093.19ms | 25388 | 1280 | 97949.4 | 9904.22 | 0.0346954 | 1.24075 | 2(Loss) | true |
| Glaze | 1694.84 | 0.113749 | 1524.18ms | 25388 | 640 | 168995 | 14285.6 | 0.463706 | 1.79059 | 3(Loss) | true |
| simdjson (ondemand) | 1248.04 | 0.0363307 | 2051.41ms | 25388 | 4890 | 242915 | 19399.9 | 0.197674 | 2.43261 | 4(Loss) | true |
