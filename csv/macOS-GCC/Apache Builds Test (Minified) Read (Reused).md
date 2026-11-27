
----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1874.77 | 0.298008 | 7011.08ms | 94653 | 640 | 1.31767e+07 | 48148.8 | 0.128101 | 1(Win) | true |
| Glaze | 1716.59 | 0.170734 | 7172.35ms | 94653 | 320 | 2.57944e+06 | 52585.6 | 0.00304257 | 2(Loss) | true |
| Jsonifier (two-stage) | 1647.64 | 0.145392 | 7506.59ms | 94653 | 320 | 2.03038e+06 | 54786.4 | 0.0014602 | 3(Loss) | true |
| simdjson (reflection) | 1165.64 | 0.0398018 | 9695.44ms | 94653 | 4890 | 4.64573e+06 | 77440.7 | 0.0280718 | 4(Loss) | true |
| simdjson (ondemand) | 978.539 | 0.0522008 | 5751.38ms | 94653 | 2560 | 5.93617e+06 | 92247.9 | 0.414867 | 5(Loss) | true |
