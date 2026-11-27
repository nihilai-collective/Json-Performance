
----
### Twitter Partial Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 9006.01 | 0.127253 | 5077.02ms | 466906 | 1280 | 5.06687e+06 | 49442.1 | 0.593237 | 0.274714 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 8992.83 | 0.11435 | 5120.2ms | 466906 | 1280 | 4.10348e+06 | 49514.6 | 0.0140225 | 0.275115 | 1(Tie) | true |
| simdjson (ondemand) | 7756.62 | 0.0636922 | 5852.71ms | 466906 | 4890 | 6.53725e+06 | 57406 | 0.158872 | 0.319008 | 3(Loss) | true |
| simdjson (reflection) | 7534.75 | 0.175373 | 5890.56ms | 466906 | 640 | 6.87427e+06 | 59096.4 | 0.193013 | 0.328399 | 4(Loss) | true |
| Glaze | 3104.33 | 0.379096 | 7389.51ms | 466906 | 40 | 1.18272e+07 | 143437 | 0.102599 | 0.797378 | 5(Loss) | true |
