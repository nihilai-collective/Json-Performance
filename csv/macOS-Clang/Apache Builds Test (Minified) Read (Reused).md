
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2314.16 | 0.0470062 | 5966.28ms | 94653 | 30 | 10085.9 | 39006.9 | 0.372303 | 1(Win) | true |
| Jsonifier (two-stage) | 1500.49 | 0.126647 | 8155.53ms | 94653 | 640 | 3.71512e+06 | 60159 | 0.0860544 | 2(Loss) | true |
| Glaze | 1293.34 | 0.165924 | 8057.94ms | 94653 | 4890 | 6.55802e+07 | 69794.7 | 0.127933 | 3(Loss) | true |
| simdjson (ondemand) | 1099.29 | 0.25883 | 5105.67ms | 94653 | 30 | 1.35518e+06 | 82115.2 | 0.0610557 | 4(Loss) | true |
