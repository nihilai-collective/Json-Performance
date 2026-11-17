
----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 716.586 | 0.318633 | 778.123ms | 4630 | 2560 | 986842 | 6161.87 | 0.920243 | 1(Win) | true |
| Jsonifier (two-stage) | 648.894 | 0.684281 | 794.402ms | 4630 | 1280 | 2.77519e+06 | 6804.67 | 0.138763 | 2(Loss) | true |
| Glaze | 554.058 | 0.132779 | 995.891ms | 4630 | 30 | 3359.14 | 7969.4 | 0.209946 | 3(Loss) | true |
| simdjson (ondemand) | 454.805 | 0.312505 | 1088.86ms | 4630 | 4890 | 4.50125e+06 | 9708.58 | 0.0143121 | 4(Loss) | true |
