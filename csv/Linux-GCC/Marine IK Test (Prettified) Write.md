
----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6235.89 | 0.0620313 | 9651.78ms | 9930848 | 320 | 2.84019e+08 | 1.51876e+06 | 0.0654051 | 0.807659 | 2.51581 | 0.147546 | 0.000326081 | 0.0250864 | 0.000593485 | 1(Win) | true |
| Glaze | 2978.22 | 0.595249 | 9830.05ms | 9930228 | 40 | 1.43306e+10 | 3.17982e+06 | 0.578763 | 1.68171 | 4.41437 | 0.474336 | 0.000715746 | 0.075734 | 0.0174977 | 2(Loss) | true |
| simdjson (reflection) | 394.289 | 0.370362 | 7274.79ms | 10018896 | 30 | 2.4165e+11 | 2.42329e+07 | 0.172727 | 12.7229 | 38.7489 | 5.79802 | 0.0227774 | 0.313614 | 0.159722 | 3(Loss) | true |
