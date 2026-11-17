
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2900.6 | 0.207509 | 163.85ms | 4669 | 40 | 405.887 | 1535.1 | 0.0499674 | 0.838204 | 1(Win) | true |
| Jsonifier (two-stage) | 2386.2 | 0.0871216 | 199.156ms | 4669 | 40 | 105.717 | 1866.03 | 0.296963 | 1.02253 | 2(Loss) | true |
| Glaze | 1789.13 | 0.0825689 | 272.91ms | 4669 | 40 | 168.91 | 2488.75 | 0.21543 | 1.36997 | 3(Loss) | true |
| simdjson (ondemand) | 638.042 | 0.315222 | 731.6ms | 4669 | 1280 | 619431 | 6978.7 | 0.564033 | 3.86406 | 4(Loss) | true |
