
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3318.45 | 0.0858652 | 608.154ms | 18245 | 40 | 810.797 | 5243.35 | 0.0403849 | 0.742162 | 1(Win) | true |
| Jsonifier | 2644.07 | 0.085083 | 742.316ms | 18245 | 40 | 1253.97 | 6580.68 | 0.052327 | 0.932757 | 2(Loss) | true |
| simdjson (ondemand) | 2127.63 | 0.126566 | 904.153ms | 18245 | 4890 | 523886 | 8178 | 0.108631 | 1.15972 | 3(Loss) | true |
| Glaze | 1982.33 | 0.0673737 | 956.924ms | 18245 | 40 | 1398.87 | 8777.45 | 0.0662244 | 1.24513 | 4(Loss) | true |
