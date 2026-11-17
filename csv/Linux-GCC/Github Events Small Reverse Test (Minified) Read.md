
----
### Github Events Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 897.019 | 0.108667 | 901.351ms | 1691 | 640 | 2442.62 | 1797.8 | 0.014951 | 5.86671 | 20.8995 | 4.14075 | 0.00196629 | 7.66928e-05 | 1.57082e-05 | 1(Win) | true |
| simdjson (ondemand) | 727.944 | 0.0498173 | 943.37ms | 1691 | 2560 | 3118.1 | 2215.37 | 0.178459 | 7.20085 | 27.851 | 5.45831 | 0.00118227 | 0.000115039 | 2.33312e-05 | 2(Loss) | true |
