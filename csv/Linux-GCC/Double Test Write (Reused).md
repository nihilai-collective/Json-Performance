
----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 928.412 | 0.175148 | 212.881ms | 1997 | 4890 | 63123.6 | 2051.34 | 0.0114439 | 2.63225 | 1(Win) | true |
| simdjson (reflection) | 743.263 | 0.0421885 | 261.319ms | 1997 | 30 | 35.0575 | 2562.33 | 0.0130073 | 3.2986 | 2(Loss) | true |
| Glaze | 595.219 | 0.0711139 | 318.253ms | 1798 | 80 | 335.757 | 2880.8 | 0.242399 | 4.1228 | 3(Loss) | true |
