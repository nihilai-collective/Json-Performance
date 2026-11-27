
----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1805.81 | 0.169086 | 627.733ms | 11812 | 2560 | 284812 | 6238.1 | 0.0080159 | 1(Win) | true |
| Jsonifier (two-stage) | 1304.15 | 0.117925 | 868.755ms | 11812 | 4890 | 507354 | 8637.67 | 0.00197219 | 2(Loss) | true |
| simdjson (reflection) | 1191.6 | 0.101559 | 951.527ms | 11812 | 4890 | 450743 | 9453.52 | 0.0118471 | 3(Loss) | true |
| Glaze | 966.106 | 0.539745 | 1160.17ms | 11812 | 320 | 1.26743e+06 | 11660 | 0.185593 | 4(Loss) | true |
| simdjson (ondemand) | 761.3 | 0.230709 | 1551.62ms | 11812 | 320 | 372918 | 14796.8 | 0.0216216 | 5(Loss) | true |
