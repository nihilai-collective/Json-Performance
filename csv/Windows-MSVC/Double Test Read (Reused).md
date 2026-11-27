
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 689.86 | 1.0634 | 252.8ms | 1811 | 4890 | 3.46594e+06 | 2503.56 | 0.0450842 | 4.35328 | 1(Win) | true |
| simdjson (ondemand) | 360.189 | 0.0727823 | 488.152ms | 1811 | 40 | 487.179 | 4795 | 0.173491 | 8.39237 | 2(Loss) | true |
