
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2703.88 | 0.604866 | 73.609ms | 1811 | 160 | 2388.36 | 638.75 | 0 | 1.09607 | 1(Win) | true |
| simdjson (stage-1) | 1119.68 | 0.254159 | 154.792ms | 1811 | 160 | 2459.12 | 1542.5 | 0.652529 | 2.68869 | 2(Loss) | true |
