
----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1963.71 | 0.0604001 | 636.574ms | 11812 | 40 | 480.204 | 5736.48 | 0.00653754 | 1(Win) | true |
| Jsonifier (two-stage) | 1470.68 | 0.0514824 | 805.746ms | 11812 | 40 | 621.994 | 7659.57 | 0.00250225 | 2(Loss) | true |
| Glaze | 1120.13 | 0.10607 | 1019.82ms | 11812 | 4890 | 556424 | 10056.7 | 0.468901 | 3(Loss) | true |
| simdjson (ondemand) | 874.831 | 0.0791248 | 1339.11ms | 11812 | 2560 | 265744 | 12876.5 | 0.0385182 | 4(Loss) | true |
