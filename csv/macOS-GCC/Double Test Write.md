
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 303.872 | 0.257312 | 638.101ms | 1997 | 2560 | 665788 | 6267.4 | 0.697151 | 1(Win) | true |
| Jsonifier | 289.828 | 0.247592 | 683.479ms | 1997 | 2560 | 677626 | 6571.1 | 0.755926 | 2(Loss) | true |
| Glaze | 160.818 | 1.42571 | 913.984ms | 1798 | 160 | 3.69738e+06 | 10662.4 | 3.41403 | 3(Loss) | true |
