
----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 885.911 | 0.0185483 | 1448.49ms | 6701 | 4890 | 8754.22 | 7213.56 | 0.0127678 | 5.83005 | 23.6004 | 4.72892 | 0.00619469 | 3.88185e-05 | 1.30921e-05 | 1(Win) | true |
| simdjson (ondemand) | 298.859 | 0.0218055 | 2888.91ms | 6701 | 2560 | 55657 | 21383.3 | 0.0460798 | 17.2592 | 84.0992 | 16.1588 | 0.0328394 | 9.85744e-05 | 5.33969e-05 | 2(Loss) | true |
