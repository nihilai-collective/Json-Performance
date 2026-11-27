
----
### Apache Builds Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12789.5 | 0.146634 | 709.441ms | 94653 | 1280 | 137102 | 7058 | 0.0509799 | 1(Win) | true |
| simdjson (reflection) | 10258.5 | 0.101457 | 896.321ms | 94653 | 4890 | 389746 | 8799.38 | 0.0217597 | 2(Loss) | true |
| Glaze | 5172.54 | 0.112985 | 1791.59ms | 94653 | 2560 | 995267 | 17451.4 | 0.145336 | 3(Loss) | true |
