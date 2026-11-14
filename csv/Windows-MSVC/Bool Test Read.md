
----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 413.945 | 0.274231 | 217.947ms | 905 | 40 | 1307.69 | 2085 | 0.239234 | 7.28843 | 1(Win) | true |
| simdjson (stage-1) | 200.744 | 0.261267 | 448.51ms | 905 | 160 | 20188.3 | 4299.38 | 0.188624 | 15.0502 | 2(Loss) | true |
