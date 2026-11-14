
----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22273.8 | 0.0739342 | 2023.55ms | 466906 | 4890 | 1.06824e+06 | 19991 | 0.00447303 | 0.110994 | 1(Win) | true |
| simdjson (stage-1) | 17036.9 | 0.168055 | 2640.57ms | 466906 | 1280 | 2.46939e+06 | 26135.9 | 0.450046 | 0.14517 | 2(Loss) | true |
