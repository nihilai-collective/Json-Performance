
----
### Discord Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 916.158 | 0.0774897 | 1417.88ms | 6701 | 640 | 18698.5 | 6975.4 | 0.0382292 | 5.58969 | 23.4323 | 4.57947 | 0.00574844 | 4.43031e-05 | 1.58558e-05 | 1(Win) | true |
| simdjson (ondemand) | 300.855 | 0.0980015 | 2840.57ms | 6701 | 320 | 138670 | 21241.4 | 0.0432715 | 16.9201 | 83.9324 | 16.1173 | 0.0314323 | 0.000112856 | 6.66878e-05 | 2(Loss) | true |
