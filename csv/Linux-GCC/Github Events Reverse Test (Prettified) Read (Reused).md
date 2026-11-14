
----
### Github Events Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1244.94 | 0.061763 | 6306.6ms | 65103 | 320 | 303607 | 49871.5 | 0.0391597 | 4.13817 | 15.1066 | 2.972 | 0.0120309 | 2.80805e-05 | 2.01604e-05 | 1(Win) | true |
| simdjson (ondemand) | 666.957 | 0.0738001 | 5463.24ms | 65103 | 640 | 3.02065e+06 | 93090.1 | 0.0242314 | 7.72074 | 28.4294 | 5.66275 | 0.0491591 | 1.77363e-05 | 5.6641e-06 | 2(Loss) | true |
