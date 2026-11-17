
----
### Google Maps Response Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1552.86 | 0.0326429 | 1302.76ms | 9378 | 4890 | 17283.9 | 5759.4 | 0.0780225 | 3.33688 | 14.654 | 2.87791 | 0.0055793 | 3.27312e-05 | 1.31056e-05 | 1(Win) | true |
| simdjson (ondemand) | 1443.42 | 0.0528475 | 1340.23ms | 9378 | 1280 | 13724.4 | 6196.07 | 0.141045 | 3.58923 | 15.4374 | 2.90051 | 0.00485686 | 2.69081e-05 | 7.4976e-06 | 2(Loss) | true |
