
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 791.53 | 0.18158 | 637.993ms | 5094 | 40 | 4967.95 | 6137.5 | 0.0949539 | 3.10988 | 1(Win) | true |
| Jsonifier (two-stage) | 712.319 | 0.215543 | 694.7ms | 5094 | 30 | 6482.76 | 6820 | 0.048852 | 3.45185 | 2(Loss) | true |
| Glaze | 629.647 | 0.15986 | 783.94ms | 5094 | 4890 | 743897 | 7715.46 | 0.133219 | 3.90766 | 3(Loss) | true |
| simdjson (ondemand) | 486.288 | 0.205593 | 1014.16ms | 5094 | 30 | 12655.2 | 9990 | 0.133645 | 5.07355 | 4(Loss) | true |
