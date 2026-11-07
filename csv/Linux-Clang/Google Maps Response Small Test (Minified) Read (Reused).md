
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2849.7 | 0.0693447 | 166.889ms | 4390 | 160 | 166.065 | 1469.15 | 0.141887 | 0.853712 | 1(Win) | true |
| Jsonifier (two-stage) | 2118.74 | 0.0891402 | 218.737ms | 4390 | 40 | 124.103 | 1976 | 0.0657462 | 1.1531 | 2(Loss) | true |
| Glaze | 1841.44 | 0.235115 | 244.25ms | 4390 | 80 | 2285.95 | 2273.56 | 0.39244 | 1.32942 | 3(Loss) | true |
| simdjson (ondemand) | 1093.51 | 0.100419 | 402.687ms | 4390 | 80 | 1182.52 | 3828.62 | 0.365631 | 2.24781 | 4(Loss) | true |
