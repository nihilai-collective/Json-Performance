
----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1500.55 | 0.13144 | 8126.53ms | 124597 | 320 | 3.46672e+06 | 79187.8 | 0.143857 | 1(Win) | true |
| Jsonifier (two-stage) | 1398.71 | 0.0618618 | 8562.51ms | 124597 | 4890 | 1.35057e+07 | 84953.5 | 0.0430676 | 2(Loss) | true |
| Glaze | 1373.05 | 0.0408003 | 8756.77ms | 124597 | 4890 | 6.09651e+06 | 86541.2 | 0.0821869 | 3(Loss) | true |
| simdjson (ondemand) | 1115.81 | 0.0785494 | 5570.28ms | 124597 | 640 | 4.47815e+06 | 106492 | 0.166425 | 4(Loss) | true |
