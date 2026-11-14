
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2281.51 | 0.0849115 | 913.501ms | 18245 | 30 | 1258.05 | 7626.43 | 0.0532949 | 1(Win) | true |
| Jsonifier | 2211.16 | 0.107829 | 927.141ms | 18245 | 4890 | 352069 | 7869.07 | 0.0164257 | 2(Loss) | true |
| simdjson (ondemand) | 1373.22 | 0.0609176 | 1416.74ms | 18245 | 40 | 2383.15 | 12670.8 | 0.13072 | 3(Loss) | true |
| Glaze | 1357.65 | 0.122943 | 1423.4ms | 18245 | 2560 | 635562 | 12816.1 | 0.0862543 | 4(Loss) | true |
