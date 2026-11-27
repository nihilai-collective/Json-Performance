
----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1431.27 | 0.0464394 | 1054.17ms | 4857 | 2560 | 5782.39 | 3236.29 | 0.338529 | 3.6052 | 14.5209 | 2.71032 | 0.00112989 | 9.49017e-05 | 4.37513e-05 | 1(Win) | true |
| simdjson (ondemand) | 1348.79 | 0.0378121 | 1076.38ms | 4857 | 4890 | 8245.55 | 3434.2 | 0.0860827 | 3.85325 | 15.3667 | 2.58122 | 0.00109512 | 6.53875e-05 | 2.5515e-05 | 2(Loss) | true |
