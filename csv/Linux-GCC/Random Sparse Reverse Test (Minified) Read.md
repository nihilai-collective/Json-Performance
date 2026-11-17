
----
### Random Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1907.14 | 0.0666246 | 5463.19ms | 409725 | 30 | 559001 | 204885 | 0.105411 | 2.69971 | 13.0839 | 2.45458 | 0.00833876 | 0.000170684 | 7.64741e-06 | 1(Win) | true |
| simdjson (ondemand) | 1413.77 | 0.0363812 | 7237.5ms | 409725 | 640 | 6.47081e+06 | 276384 | 0.0185538 | 3.62126 | 14.7733 | 2.68278 | 0.0144641 | 0.000169039 | 2.13291e-05 | 2(Loss) | true |
