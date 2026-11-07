
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1017.74 | 0.203075 | 468.114ms | 4857 | 80 | 6833.86 | 4551.25 | 0.0274725 | 2.4137 | 1(Win) | true |
| Jsonifier (two-stage) | 830.851 | 0.238155 | 573.52ms | 4857 | 40 | 7051.28 | 5575 | 0.0299043 | 2.95879 | 2(Loss) | true |
| Glaze | 824.199 | 0.271802 | 588.263ms | 4857 | 40 | 9333.33 | 5620 | 0.118483 | 2.99131 | 3(Loss) | true |
| simdjson (ondemand) | 683.185 | 0.258868 | 703.274ms | 4857 | 30 | 9241.38 | 6780 | 0.04914 | 3.60531 | 4(Loss) | true |
