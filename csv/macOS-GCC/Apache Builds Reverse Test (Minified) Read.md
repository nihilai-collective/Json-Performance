
----
### Apache Builds Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 830.868 | 0.225312 | 5640.37ms | 94653 | 160 | 9.58721e+06 | 108643 | 0.305388 | 1(Win) | true |
| simdjson (ondemand) | 489.011 | 0.0844355 | 9778.38ms | 94653 | 640 | 1.55475e+07 | 184593 | 0.0729722 | 2(Loss) | true |
