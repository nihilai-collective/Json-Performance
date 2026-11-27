
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2297.06 | 0.262887 | 79.4926ms | 1811 | 640 | 2500.39 | 751.875 | 0.124844 | 1.03623 | 1(Win) | true |
| simdjson (stage-1) | 962.175 | 0.342609 | 183.607ms | 1811 | 40 | 1512.82 | 1795 | 0.0929368 | 2.53214 | 2(Loss) | true |
