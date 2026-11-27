
----
### Marine IK Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 888.087 | 0.037297 | 643.709ms | 4604 | 320 | 1088.07 | 4944.02 | 0.100728 | 1(Win) | true |
| Jsonifier (two-stage) | 725.989 | 0.0637975 | 748.933ms | 4604 | 80 | 1190.99 | 6047.91 | 0.000620045 | 2(Loss) | true |
| Glaze | 450.786 | 0.0539901 | 1180.44ms | 4604 | 80 | 2212.32 | 9740.14 | 0.0815592 | 3(Loss) | true |
| simdjson (ondemand) | 375.631 | 0.0568439 | 1310.35ms | 4604 | 4890 | 215886 | 11688.9 | 0.195263 | 4(Loss) | true |
