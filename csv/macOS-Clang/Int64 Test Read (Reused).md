
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2679.65 | 0.0734681 | 148.324ms | 3862 | 320 | 326.3 | 1374.47 | 0.0399995 | 1(Win) | true |
| Jsonifier | 2662.47 | 0.145989 | 148.904ms | 3862 | 80 | 326.277 | 1383.34 | 0.296407 | 2(Loss) | true |
| Glaze | 1444.66 | 0.0876531 | 258.96ms | 3862 | 1280 | 6391.98 | 2549.44 | 0.106816 | 3(Loss) | true |
| simdjson (ondemand) | 638.221 | 0.0898636 | 625.721ms | 3862 | 30 | 806.809 | 5770.87 | 0.239137 | 4(Loss) | true |
