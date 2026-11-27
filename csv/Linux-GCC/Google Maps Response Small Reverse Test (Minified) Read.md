
----
### Google Maps Response Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 820.405 | 0.0336065 | 1232.06ms | 4390 | 2560 | 7529.36 | 5103.12 | 0.104835 | 6.32043 | 28.3674 | 5.72164 | 0.0118457 | 0.000141301 | 7.18964e-05 | 1(Win) | true |
| simdjson (ondemand) | 710.389 | 0.0710723 | 1313.58ms | 4390 | 320 | 5614.2 | 5893.44 | 0.00996772 | 7.29842 | 31.2219 | 6.05991 | 0.0128666 | 4.91173e-05 | 2.42027e-05 | 2(Loss) | true |
