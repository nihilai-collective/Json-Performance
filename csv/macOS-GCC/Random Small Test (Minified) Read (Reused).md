
----
### Random Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1691.27 | 0.522171 | 396.153ms | 5094 | 2560 | 575911 | 2872.4 | 1.19786 | 1(Win) | true |
| Jsonifier (two-stage) | 1133.99 | 0.680335 | 567.628ms | 5094 | 640 | 543656 | 4284 | 1.5625 | 2(Loss) | true |
| Glaze | 991.937 | 0.249162 | 604.152ms | 5094 | 4890 | 728151 | 4897.51 | 0.451143 | 3(Loss) | true |
| simdjson (reflection) | 883.054 | 0.450935 | 661.373ms | 5094 | 4890 | 3.0094e+06 | 5501.38 | 1.89821 | 4(Loss) | true |
| simdjson (ondemand) | 795.772 | 0.260621 | 754.22ms | 5094 | 4890 | 1.23786e+06 | 6104.79 | 0.728689 | 5(Loss) | true |
