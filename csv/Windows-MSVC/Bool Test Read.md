
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 642.139 | 0.135004 | 138.969ms | 905 | 2560 | 8428.98 | 1344.06 | 0.0638978 | 4.67091 | 1(Win) | true |
| Glaze | 626.41 | 1.14773 | 140.796ms | 905 | 4890 | 1.22283e+06 | 1377.81 | 0.0368236 | 4.78667 | 2(Loss) | true |
| simdjson (ondemand) | 182.597 | 0.267098 | 498.81ms | 905 | 30 | 4781.61 | 4726.67 | 0.212014 | 16.5958 | 3(Loss) | true |
