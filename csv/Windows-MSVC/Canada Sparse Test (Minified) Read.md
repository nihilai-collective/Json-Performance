
----
### Canada Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8413.04 | 0.0514978 | 6048.37ms | 2090234 | 640 | 9.52886e+06 | 236942 | 0.00718742 | 0.361196 | 1(Win) | true |
| simdjson (ondemand) | 6436.55 | 0.155665 | 7894.06ms | 2090234 | 160 | 3.71864e+07 | 309701 | 0.0607073 | 0.472138 | 2(Loss) | true |
