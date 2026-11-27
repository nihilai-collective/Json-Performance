
----
### Apache Builds Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18400.8 | 0.0426493 | 1440.7ms | 136037 | 640 | 5786.85 | 7050.49 | 0.147058 | 0.275789 | 0.929652 | 0.125958 | 2.67505e-05 | 3.75587e-06 | 1.60802e-06 | 1(Win) | true |
| Glaze | 7235.71 | 0.0389962 | 2529.43ms | 136076 | 4890 | 239196 | 17935 | 0.118402 | 0.696382 | 3.79803 | 0.637813 | 5.17815e-05 | 4.7264e-06 | 1.49231e-06 | 2(Loss) | true |
| simdjson (reflection) | 642.05 | 0.134048 | 5310.77ms | 136037 | 1280 | 9.39096e+07 | 202064 | 0.0859994 | 7.85924 | 34.7218 | 7.10838 | 0.0276165 | 0.00673625 | 6.53659e-05 | 3(Loss) | true |
