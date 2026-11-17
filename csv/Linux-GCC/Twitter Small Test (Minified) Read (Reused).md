
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3131.85 | 0.168356 | 821.947ms | 2889 | 40 | 87.7429 | 879.725 | 0.0786849 | 1.69039 | 5.59086 | 0.858082 | 0.000346141 | 6.92281e-05 | 0 | 1(Win) | true |
| Glaze | 2590.72 | 0.0447899 | 835.856ms | 2889 | 2560 | 580.838 | 1063.48 | 0.216483 | 2.06132 | 8.32399 | 1.40222 | 0.000347493 | 6.40901e-05 | 3.42084e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2499.2 | 0.0578482 | 846.025ms | 2889 | 4890 | 1988.75 | 1102.42 | 0.286771 | 2.1088 | 7.39495 | 1.03669 | 0.00047136 | 0.000103842 | 3.06501e-05 | 3(Loss) | true |
| simdjson (reflection) | 2136.71 | 0.111822 | 864.727ms | 2889 | 640 | 1330.58 | 1289.44 | 0.0547418 | 2.44367 | 8.72343 | 1.17342 | 0.000519752 | 0.000164417 | 8.05858e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1443.61 | 0.0572507 | 928.013ms | 2889 | 2560 | 3056.33 | 1908.53 | 0.164582 | 3.5948 | 11.7099 | 2.31395 | 0.000352631 | 0.000111144 | 2.90704e-05 | 5(Loss) | true |
