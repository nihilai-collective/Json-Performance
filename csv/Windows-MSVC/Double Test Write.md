
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 466.929 | 0.128598 | 425.581ms | 1997 | 80 | 2200.95 | 4078.75 | 0.639464 | 5.2491 | 1(Win) | true |
| Glaze | 130.707 | 0.37713 | 1337.97ms | 1798 | 2560 | 6.26625e+06 | 13118.8 | 0.357223 | 18.8909 | 2(Loss) | true |
