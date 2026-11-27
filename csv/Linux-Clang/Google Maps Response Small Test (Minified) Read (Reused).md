
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1423.05 | 0.101914 | 1040.9ms | 4390 | 640 | 5753.61 | 2942.02 | 0.0567003 | 3.66772 | 16.6216 | 3.04055 | 0.0025242 | 0.000108912 | 3.98633e-05 | 1(Win) | true |
| simdjson (ondemand) | 1150.14 | 0.0606889 | 1116.78ms | 4390 | 4890 | 23864.7 | 3640.1 | 0.0437117 | 4.50901 | 18.7929 | 3.17813 | 0.00419586 | 9.36317e-05 | 4.50457e-05 | 2(Loss) | true |
