
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2184.55 | 2.36099 | 188.62ms | 3808 | 160 | 246479 | 1662.4 | 0.0963391 | 1(Win) | true |
| Jsonifier (two-stage) | 2079.6 | 0.4933 | 185.748ms | 3808 | 4890 | 362883 | 1746.3 | 0.749837 | 2(Loss) | true |
| Glaze | 1741.27 | 0.773937 | 214.939ms | 3808 | 1280 | 333490 | 2085.6 | 1.65724 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1315.79 | 1.64651 | 255.144ms | 3808 | 320 | 660843 | 2760 | 2.67857 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1278.32 | 0.611868 | 288.733ms | 3808 | 4890 | 1.47755e+06 | 2840.92 | 0.0626367 | 4(Tie) | true |
