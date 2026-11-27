
----
### Discord Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 815.851 | 0.140591 | 576.767ms | 4857 | 640 | 40776.2 | 5677.5 | 0.0605094 | 3.71037 | 1(Win) | true |
| simdjson (ondemand) | 741.945 | 0.0823745 | 632.649ms | 4857 | 2560 | 67704.7 | 6243.05 | 0.0513334 | 4.08134 | 2(Loss) | true |
