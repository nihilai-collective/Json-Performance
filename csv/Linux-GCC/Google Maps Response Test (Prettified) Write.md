
----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 21154.7 | 0.0993488 | 874.143ms | 31235 | 1280 | 2504.98 | 1408.1 | 0.00704577 | 0.245788 | 0.668225 | 0.0968465 | 3.25156e-05 | 1.44569e-05 | 3.82684e-06 | 1(Win) | true |
| Glaze | 6677.36 | 0.061234 | 1184.37ms | 31235 | 4890 | 36489.5 | 4461.05 | 0.164713 | 0.763722 | 3.75185 | 0.631087 | 0.000722264 | 2.16055e-05 | 1.15426e-05 | 2(Loss) | true |
| simdjson (reflection) | 532.752 | 0.182482 | 6366.32ms | 31235 | 2560 | 2.66509e+07 | 55913.5 | 0.0511116 | 9.43606 | 38.2381 | 7.0414 | 0.0151276 | 0.000142681 | 9.24819e-05 | 3(Loss) | true |
