
----
### Canada Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1954.42 | 0.0594016 | 1388.04ms | 11579 | 640 | 7209.11 | 5650.05 | 0.126829 | 2.64799 | 13.2513 | 2.28837 | 0.00175979 | 1.75425e-05 | 3.23862e-06 | 1(Win) | true |
| Jsonifier (generic) | 1879.77 | 0.0734761 | 1405.72ms | 11579 | 640 | 11923.5 | 5874.44 | 0.201889 | 2.7299 | 12.6663 | 2.4186 | 0.00217487 | 1.71377e-05 | 8.09655e-07 | 2(Loss) | true |
