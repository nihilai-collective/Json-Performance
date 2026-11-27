
----
### Marine IK Reverse Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6182.22 | 0.0710589 | 9895.3ms | 10018896 | 80 | 9.6489e+07 | 1.54552e+06 | 0.108391 | 0.400459 | 1(Win) | true |
| Glaze | 3458.03 | 0.272366 | 8508.44ms | 9930228 | 40 | 2.2255e+09 | 2.73861e+06 | 0.374842 | 0.715945 | 2(Loss) | true |
| simdjson (reflection) | 222.371 | 0.587616 | 12821.1ms | 10018896 | 30 | 1.91246e+12 | 4.29677e+07 | 2.27263 | 11.1336 | 3(Loss) | true |
