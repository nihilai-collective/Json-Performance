
----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 768.565 | 0.0914145 | 1263.43ms | 4390 | 160 | 3967.51 | 5447.33 | 0.0393696 | 6.75036 | 29.8093 | 5.97062 | 0.01124 | 5.69476e-05 | 1.42369e-06 | 1(Win) | true |
| simdjson (ondemand) | 693.127 | 0.0377835 | 1326.27ms | 4390 | 1280 | 6666.8 | 6040.21 | 0.0467093 | 7.47785 | 33.349 | 6.12506 | 0.00877794 | 0.000100014 | 3.34567e-05 | 2(Loss) | true |
