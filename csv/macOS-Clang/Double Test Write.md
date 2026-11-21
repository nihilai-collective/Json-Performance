
----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 317.032 | 0.104871 | 621.479ms | 1997 | 40 | 1587.53 | 6007.25 | 0.00527169 | 1(Win) | true |
| Glaze | 216.592 | 0.0922312 | 817.406ms | 1798 | 40 | 2132.6 | 7916.75 | 0.0511312 | 2(Loss) | true |
